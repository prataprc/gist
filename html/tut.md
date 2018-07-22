HTML5 - DOM core - DOM events - NPAPI - URI - Unicode - ECMAScript - HTTP -
CSS3 - MIME - SVG - WebSckets (Communication) - Geolocation - XHR - WebGL -
WebM - MathML

DOM Core : 

- Node property,
    type
    parentNode
    childNodes
    ownerDocument
    elements
      The elements object (array) allows you to access any element within a form
      generically, via a loop for example. Each element inside the form is stored
      as an array element inside elements[].

- CDATASections are also considered as TextNodes.

HTML : 

- For attributes, the value, along with the "=" character, can be omitted
  altogether if the value is the empty string.

ECMAScript : 

- The navigator.yieldForStorageUpdates() method, in this model, is equivalent to
  allowing other scripts to run while the calling script is blocked.

- However, for historical reasons not all of the spaces and line breaks in the
  original markup appear in the DOM. In particular, all the whitespace before
  head start tag ends up being dropped silently, and all the whitespace after
  the body end tag ends up placed at the end of the body.

Serializability of script evaluation : 



- Javascript supports special content properties on the DOM node, for instance,
  anchor element's DOM contains properties like, `href`, `host`, `protocol` etc.
  
- The majority of presentational features from previous versions of HTML are no
  longer allowed.

- Use of the style attribute is somewhat discouraged in production environments,
  but it can be useful for rapid prototyping and for providing specific
  styles in unusual cases where a separate style sheet would be inconvenient.

- ownerDocument, parentNode, childNodes
