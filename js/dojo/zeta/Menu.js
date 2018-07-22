dojo.declare("zeta.Menu",
	[ dijit._Widget, dijit._Templated, dijit._KeyNavContainer ],
	{
        _items: [],         // List of items added to the Menu.

        title: "",          // Menu title

        _titlestyle: { background: "#f3f6f0" }, // Style attribute for title item.

        titlestyle: {},     // Style attribute for title item.

        targetNodes: [],    // Target nodes for which the menu should be activated

        style: {},          //

        _style: { position: "fixed", border: "1px solid gray", background: "#FFFFFF" },

        _visible: false,

        templateString: '<div></div>',

        postCreate: function() {
            dojo.forEach(
                this.targetNodes,
                function( n ) {
                    n = dojo.isString( n ) ? dojo.byId( n ) : n;
                    dojo.connect( n, "onclick", this, "onClick" );
                },
                this
            );
            if( this.title ) {
                this.addItem( 
                        new zeta.MenuItem(
                            { content: this.title, 
                              style: dojo.mixin( {}, this._titlestyle, this.titlestyle )
                            })
                );
            }
            dojo.style( this.domNode, dojo.mixin( {}, this._style, this.style ));
            dojo.connect( this.domNode, "onblur", this, "onBlur" );
            dojo.fx.wipeOut({ node : this.domNode, duration : 0 }).play();
            dojo.place( this.domNode, dojo.body(), "last" );
        },

        addItem: function( w ) {
            var items = this._items;
            items[items.length] = w;
            dojo.place( w.domNode, this.domNode, "last" );
        },

        destroy: function() {
        },

        onClick: function( e ) {
            if( this._visible ) {
                dojo.fx.wipeOut({ node : this.domNode, duration : 20 }).play();
                this._visible = false;
            } else {
                box = dojo.coords( e.currentTarget );
                dojo.marginBox(this.domNode, { l: box.l, t: (box.t + box.h) });
                dijit.focus( this.domNode );
                dojo.fx.wipeIn({ node : this.domNode, duration : 20 }).play();
                this._visible = true;
            }
            dojo.stopEvent( e );
        },

        onBlur: function() {
            dojo.fx.wipeOut({ node : this.domNode, duration : 20 }).play();
            this._visible = false;
        }
    }
);

