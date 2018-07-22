ct_template='\
<div>\
    <div class="curvy4 bggrn2"></div>\
    <div class="curvy2 bggrn2">\
        <div class="bggrn2" style="height : 1px ; margin: 0px 2px 0px 2px;" ></div>\
    </div>\
    <div class="curvy1 bggrn2">\
        <div class="bggrn2" style="height : 1px ; margin: 0px 1px 0px 1px;"></div>\
    </div>\
    <div class="bggrn2">\
        <div class="bggrn2 p5" style="margin: 0px 1px 0px 1px;">\
            <div name="content">\
                <div style="height: 1.2em;"></div>\
                <div class="bgwhite p10"></div>\
            </div>\
        </div>\
    </div>\
    <div class="curvy1 bggrn2">\
        <div class="bggrn2" style="height : 1px ; margin: 0px 1px 0px 1px;"></div>\
    </div>\
    <div class="curvy2 bggrn2">\
        <div class="bggrn2" style="height : 1px ; margin: 0px 2px 0px 2px;" ></div>\
    </div>\
    <div class="curvy4 bggrn2"></div>\
</div>\
'
dojo.declare( 'zeta.ConfigTabs',
  [ dijit._Widget, dijit._Templated, dijit._KeyNavContainer ],
  {
    id: '',             // Id attribute the configuration tabs

    tabs: [],           // List of nodes to be contained as tabs

    currtab: null,      // Current tab that is being shown

    currtitle: null,    // Current title node that is being shown

    templateString: ct_template, 

    postCreate: function() {
        this.contnode = dojo.query( "[name=content]", this.domNode )[0];
        console.log( this.domNode.parentNode )
        var titles = this.contnode.childNodes[1]
        var contnr = this.contnode.childNodes[3]
        dojo.forEach(
            this.tabs,
            function( tab ) {
                var tn = this._maketitle( tab  )
                dojo.toggleClass( tab, "dispnone", true )
                dojo.place( tn, titles, "last" );
                dojo.place( tab, contnr, "last" );
                if( (this.currtab==null) && dojo.hasAttr( tab, "selected" )) {
                    this._switchtab( tn, tab );
                }
            }, this
        );
    },

    _maketitle: function( tab ) {
        var title = dojo.attr( tab, "title" )
        var n = dojo.create(
                    "span",
                    { class: "p3 mr5 fntbold fntsmall fgblue pointer",
                      innerHTML: title }
                )
        dojo.connect( n, "onclick", dojo.hitch( this, "_switchtab", n, tab ) )
        return n 
    },

    _switchtab: function( tn, tab, e ) {
        var contnr = this.contnode.childNodes[3];
        if( this.currtitle ) { 
            dojo.toggleClass( this.currtitle, "bgwhite", false );
            dojo.toggleClass( this.currtitle, "fgblue", true );
            dojo.toggleClass( this.currtab, "dispnone", true );
        }
        dojo.toggleClass( tn, "bgwhite", true );
        dojo.toggleClass( tn, "fgblue", false );
        dojo.toggleClass( tab, "dispnone", false );
        this.currtab     = tab;
        this.currtitle   = tn;
    }

  }
);

