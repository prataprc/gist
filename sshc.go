package main

import (
	"bytes"
	"code.google.com/p/go.crypto/ssh"
	"crypto"
	"crypto/rsa"
	"crypto/x509"
	"encoding/pem"
	"errors"
	"flag"
	"fmt"
	"io"
	"io/ioutil"
	"net"
	"os"
	"path"
)

var NEWLINE = []byte{10} // '\n'

var options struct {
	privateKey     string // File containing ssh private key
	authorizedKeys string // File containing ssh authorized_keys
	username       string
	password       string
}

type AuthorizedKey struct {
	out     ssh.PublicKey
	comment string
	options []string
}

func argParse() {
	username := os.Getenv("USER")
	authkeys := path.Join(os.Getenv("HOME"), ".ssh", "authorized_keys")
	flag.StringVar(&options.username, "-u", username,
		"Specify file containing ssh authorized keys")
	flag.StringVar(&options.password, "-p", "",
		"Specify file containing ssh authorized keys")
	flag.StringVar(&options.authorizedKeys, "-authkeys", authkeys,
		"Specify file containing ssh authorized keys")
	flag.StringVar(&options.privateKey, "-privkey", "",
		"Specify file containing ssh private key")
	flag.Parse()
}

// keyChain implements the ClientKeyring interface
type keyChain struct {
	key *rsa.PrivateKey
}

func (k *keyChain) Key(i int) (ssh.PublicKey, error) {
	if i != 0 {
		return nil, nil
	}
	return ssh.NewPublicKey(&k.key.PublicKey)
}

func (k *keyChain) Sign(i int, rand io.Reader, data []byte) ([]byte, error) {
	hashFunc := crypto.SHA1
	h := hashFunc.New()
	h.Write(data)
	digest := h.Sum(nil)
	return rsa.SignPKCS1v15(rand, k.key, hashFunc, digest)
}

func (k *keyChain) LoadPEM(file string) error {
	buf, err := ioutil.ReadFile(file)
	if err != nil {
		return err
	}
	block, _ := pem.Decode(buf)
	if block == nil {
		return errors.New("ssh: no key found")
	}
	if k.key, err = x509.ParsePKCS1PrivateKey(block.Bytes); err != nil {
		return err
	}
	return nil
}

// password implements the ClientPassword interface
type password string

func (p password) Password(user string) (string, error) {
	fmt.Println(user)
	return string(p), nil
}

func main() {
	argParse()
	options.privateKey = path.Join(os.Getenv("HOME"), ".ssh", "id_rsa")
	//clientKey := new(keyChain)
	//if err := clientKey.LoadPEM(options.privateKey); err != nil {
	//    panic(err)
	//}

	// SSH setup, we assume current username and use the ssh agent for auth
	agent_sock, err := net.Dial("unix", os.Getenv("SSH_AUTH_SOCK"))
	if err != nil {
		panic(err)
	}
	defer agent_sock.Close()

	config := &ssh.ClientConfig{
		User: "prataprc",
		Auth: []ssh.ClientAuth{
			// ClientAuthPassword wraps a ClientPassword implementation in a type
			// that implements ClientAuth.
			ssh.ClientAuthPassword(password("")),

			ssh.ClientAuthAgent(ssh.NewAgentClient(agent_sock)),

			// ClientAuthPublickey wraps a ClientKeyring implementation in a type
			// that implements ClientAuth.
			//ssh.ClientAuthKeyring(clientKey),
		},
	}
	client, err := ssh.Dial("tcp", "localhost:22", config)
	if err != nil {
		panic(err)
	}
	session, err := client.NewSession()
	if err != nil {
		panic(err)
	}
	out, _ := session.CombinedOutput("find ./")
	fmt.Println(string(out))
	session.Close()
}

func parseAuthorizedKeys() []AuthorizedKey {
	bs, err := ioutil.ReadFile(options.authorizedKeys)
	if err != nil {
		panic(err)
	}
	authkeys := make([]AuthorizedKey, 0)
	for _, line := range bytes.Split(bs, NEWLINE) {
		if out, comment, options, _, ok := ssh.ParseAuthorizedKey(line); ok {
			authkeys = append(authkeys, AuthorizedKey{
				out: out, comment: comment, options: options})
		}
	}
	return authkeys
}

func parsePrivateKey() {
	if options.privateKey != "" {
		bs, err := ioutil.ReadFile(options.privateKey)
		if err != nil {
			panic(err)
		}
		fmt.Println(ssh.ParsePrivateKey(bs))
	}
}
