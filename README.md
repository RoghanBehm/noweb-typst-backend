# noweb Typst

A typst backend for literate programming tool **noweb**

## Overview

In typical use of noweb, `noweave` generates documentation by passing the noweb markup stream through the LaTeX backend, producing a `.tex` file which can then be compiled to PDF:
`nw --> markup --> LaTeX --> PDF`


This project replaces the LaTeX step with a Typst emitter:
`nw --> markup --> Typst --> PDF`


## Usage

`build/noweb-typst <markup file name> <code language name>`


> [!NOTE]
> The code language name is passed so that code blocks can be emitted
> with proper syntax highlighting (e.g. ```python).
