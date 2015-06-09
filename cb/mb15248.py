from __future__ import with_statement
from __future__ import print_function
import fabric
import fabric.utils
from fabric.api import *
from fabric.contrib.console import confirm
import os
import httplib

# to repro https://issues.couchbase.com/browse/MB-14116

user, homedir = os.environ['USER'], os.environ['HOME']
cbidxdir = os.sep.join([homedir, "devgo/src/github.com/couchbase/indexing"])
gopath = os.environ.get("GOPATH", "")
goroot = os.environ.get("GOROOT", "")

def setenv(attr="", force=None, default=None) :
    if force :
        setattr(env, attr, force)
    elif attr != "" and (not hasattr(env, attr) or not getattr(env, attr)) :
        setattr(env, attr, default)

map(lambda kwargs: setenv(**kwargs), [
    {"attr": "user", "force": user},
    {"attr": "hosts", "default": ["localhost"]},
    {"attr": "gopath", "default": gopath},
    {"attr": "goroot", "default": goroot},
])

fabric.state.output["running"] = False
fabric.state.output["stdout"] = False

#--- tasks

@task
def mb15248():
    print("Make sure that KV is populated with atleast 1000 documents")
    cmdfmt = "./cbindex -server 127.0.0.1:9000 -auth Administrator:asdasd %s"
    with cd(os.sep.join([cbidxdir, "secondary", "cmd", "cbindex"])), shell_env(GOPATH=env.gopath, GOROOT=env.goroot) :

        trycmd("go build", op="local", v=True)
        trycmd(cmdfmt % ("-type list",), op="local", v=True)

        indx1 = """-type create -bucket default -index myindex1_0 -fields=email """ \
                """-with="{\\\"defer_build\\\":true} " -where='email < 7fffff'"""
        trycmd(cmdfmt % (indx1,), op="local")
        trycmd(cmdfmt % ("-type list",), op="local", v=True)

        indx2 = """-type create -bucket default -index myindex1_1 -fields=email """ \
                """-with=" {\\\"defer_build\\\":true} " -where='email >= 7fffff'"""
        trycmd(cmdfmt % (indx2,), op="local")
        trycmd(cmdfmt % ("-type list",), op="local", v=True)

#---- local functions

def pp_for_host(host_string) :
    def fn(*args, **kwargs) :
        msg = "[%s] " % host_string
        msg += " ".join(map(str, args))
        msg += "\n".join(map(lambda k, v: "   %s: %s" % (k, v), kwargs.items()))
        if msg.lower().find("error") > 0 :
            fabric.utils.error(msg)
        else :
            print(msg)
    return fn

def trycmd(cmd, op="run", v=False):
    oldstdout = fabric.state.output["stdout"]
    oldstderr = fabric.state.output["stderr"]
    if v :
        fabric.state.output["stdout"] = True
        fabric.state.output["stderr"] = True

    pp = pp_for_host(env.host_string)
    out = {"sudo": sudo, "run": run, "local": local}[op](cmd) # execute

    fabric.state.output["stdout"] = oldstdout
    fabric.state.output["stderr"] = oldstderr

    if out.failed :
        pp("cmd failed: %s" % cmd)
        pp(out)
        return out.failed
    else :
        pp(cmd, ": ok")
    return out.succeeded
