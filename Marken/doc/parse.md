# Introduction

This is the document about how **Marken** convert your Markdown document to HTML format. The main principle is to follow the guide in [Markdown Syntax Document](http://daringfireball.net/projects/markdown/syntax). Besides that, we will focus on [GitHub Flavored Markdown](https://help.github.com/articles/github-flavored-markdown).

# Parsing

## Standard Markdown Syntax

### Header

There are two styles of headers, Setext and atx.

#### Setext-style

Setext-style headers are "underlined" using equal signs (for first-level headers) and dashes (for second-level headers). For example:

    This is an H1
    =============
    
    This is an H2
    -------------

Actually, the headers using underscore also meet the condition of the horizontal rules. So they will transformed to:

    <h1>This is an H1</h1>
    <hr>
    <h2>This is an H2</h1>
    <hr>

#### Atx-style

Atx-style headers begins with 1~6 hash characters, any number of hash characters in the end of line will be ignored. For example:

    # This is an H1
    ## This is an H2
    ### This is an H3 ###

They will trans formed to:

    <h1>This is an H1</h1>
    <h2>This is an H2</h2>
    <h3>This is an H3</h3>

### Code Block

The text block width the indentation of at least 4 spaces or 1 tab will be treated as code block. For example:

    #include <cstdio>
    
    int main() {
        return 0;
    }

Note that the code will have no syntax highlight because they simply transformed to:

    <pre><code>
    #include &lt;cstdio&gt
    
    int main() {
        return 0;
    }
    </code></pre>

### Inline Link

For example:

    [Text](http://website/ "Title")

Transformed to:

    <a href="http://website/" title="Title">Text</a>

## GitHub Flavored Markdown

Not yet.