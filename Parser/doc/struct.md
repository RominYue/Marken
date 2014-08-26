# Overview

This is the document about how the Markdown parser is designed. We aimed at creating a static library which could easily be used for syntax highlighting and HTML compiling. The code will be writen by standard C++11, which is widely supported nowadays. See [Markdown: Syntax](http://daringfireball.net/projects/markdown/syntax) and [GitHub Flavored Markdown](https://help.github.com/articles/github-flavored-markdown) for more syntax details.

# Specifications

* Input is **UTF-8** signed byte array with no BOM.

  Only a few ASCII characters have an influence on the semantic of the document, while other non-ASCII characters in UTF-8 is represented by a group of negative bytes, thus we can simply ignore the negative bytes.

* Parsing is done **line by line**.

  In order to used for syntax highlighting, the parser should have the ability to reconstruct the structure information when a line is edited with minimal operations. The next line, however, should be reparsed when the structure of current line is changed.

* Output has the same line number as the input.

  There is no extra spaces in the output result.

# Design

## Analysis

### Special Characters

The following characters might affect the semantic:

    \ Escape character
    ` Inline code (GitHub flavor: fanced code blocks)
    * Emphasis, unordered list
    _ Emphasis, unordered list, horizontal rule (GitHub Flavored: multiple underscores in words)
    ~ (GitHub Flavored: strikethrough)
    : reference link
    [] Inline link, reference link, image, link label
    () Inline link, image
    < Block HTML, inline HTML
    > Block HTML, inline HTML, block quote
    # Atx header
    + Unordered list
    - Horizontal rule, setext header, unordered list (GitHub Flavored: table)
    | (GitHub Flavored: table)
    = Horizontal rule, setext header
    ! Image
    0-9 Ordered list
    . Ordered list
    \s\t Code block

### Block Elements

Beacause Markdown allow empty lines in block elements, the block information should be inherited from the last line except the headers.

### Span Elements

## Structure

## Dynamic Reconstruction