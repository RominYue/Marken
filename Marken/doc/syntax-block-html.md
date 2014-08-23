## Block-level HTML elements

### Description

Block-level HTML elements must have closed tags with no indention. The elements include `<div>`, `<table>`, `<pre>`, `<p>`, etc. Contents inside block-level HTML elements will be treated as plain HTML text, and no Markdown syntax will take effect.

Example:

    <table>
      <tr>
        <td>Foo</td>
      </tr>
    </table>

### Rule

Block-level HTML elements include: `<address>`, `<blockquote>`, `<ol>`, `<p>`, `<pre>`, `<table>`, `<ul>`. Some block-level elements are not listed because they are not suitable for text-based document.

* The root tag is not closed.

The remaining document will be treated as HTML block.
