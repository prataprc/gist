dojo.declare( "zeta.MenuItem",
	[ dijit._Widget, dijit._Templated, dijit._KeyNavContainer ],
	{  
        content: '',    // Menu item name, can also be a valid html string

        _style: { padding: "2px 5px" },

        style: {},    // style for menu item

        templateString: '<div dojoAttachEvent="onclick:onClick"></div>',

        postCreate: function() {
            var l     = this.content ? this.content : "...";
            var style = l == "..." ? { color: "gray" } : {};

            if( dojo.isString( l ) && (l[0] != '<') ) {
                this.domNode.innerHTML = l;
            } else {                                        // Is html ?
                dojo.place( l, this.domNode, "first" );
            }
            dojo.style( this.domNode, dojo.mixin( style, this._style, this.style ));
        },

        destroy: function() {
        },

        onClick: function( e ) { dojo.stopEvent(e); }
    }
);


