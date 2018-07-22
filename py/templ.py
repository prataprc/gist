a = '<html>
    <head>

        <title>Zebu</title>




    <link href="/style1.css" rel="stylesheet" type="text/css"></link>



    <script src="/jquery.js" type="text/javascript"></script>
    <script src="/zetaclient.js" type="text/javascript"></script>

    </head>
    <body>

    <div id="men">
                <a title="Sign in if already registered" href="/accounts/signin">signin</a> |
                <a title="New User ? Sign up" href="/accounts/newaccount?id=form">register</a> |
                <a title="Explore registered users" href="/">users</a> |
                <a title="Explore projects underZebu" href="/">projects</a> |
                <a title="About Us" href="/">aboutus</a> |
                <a title="Learn how to use Zebu" href="/">help</a> |
    </div>


    <table id="logo" cellspacing="0" cellpadding="0">
    <tr>
        <td width="100">
            <a href=/><img width="100" height="75" src=/zebu-100x75.jpg /></a>
        </td>
        <td width="100" style="padding-left: 1.5em;">
            <span style="font : caption;">No Project Logo</span>
        </td>
        <td style="text-align: right;">
        <input name="sr" size="64"/>
        <input id=srbox type="submit" value="Search remove!" name="top_search"/>
        </td>
    </tr>
    </table>


    <div>
    </div>



    <table class="tab" cellspacing="0" cellpadding="0" border="0">
        <tr><th>
            <div class="active">
                <div class="curvy4"></div>
                <div class="curvy2"></div>
                <div class="curvy1"></div>
                <div style="text-align: left; padding-left: 10px;">
                    Sign In
                </div>
            </div>
        </tr></th>
    </table>
    <br/>

    <p>
    <table id="acf" frame="box">

<form
    action=%s
    method="post" name="acform">
    <tr>
        <td style="width: 100%;">
            <fieldset id="fset"><legend id="legend" style="color: #FD0606;">Login Details :</legend>
            <table style="width: 100%;">
                    <tr><td valign="top" style="text-align: right;"><label for="loginame">Login Name :</label></td>
                        <td>
                        <div>
                                <input class="req" id="" type="text" name="loginame"
                                       size="16" maxlength="32"></input>
                        </div>
                        </td>
                    <tr>
            </table>
            </fieldset>
            <br/>
        </td>
    </tr>
    <tr><td colspan="2" align="center"><input name=acform type="submit" value="Submit"/></td></tr>
    </form>

    </table>
    </p>

    <br/>


    <div>
        <hr></hr>
        <table>
            <tr>
                <td rowspan="2"><a href=/><img width="110" height="45" src=/zeta-110x45.jpg /></a></td>
                <td id="footer" valign="bottom">Version 0.1</td>
            </tr>
            <tr>
                <td id="footer" valign="top">SKR Farms</td>
            </tr>
        </tr></table>
    </div>

    </body>
</html>
'


