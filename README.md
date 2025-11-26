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
## Generating the Markup Stream

This backend consumes the **markup** output produced by noweb’s `markup`
tool (the first stage of the noweb pipeline).  
If `markup` is on your `PATH`, you can run:

```bash
markup wordcount.nw > wordcount.nwm
build/noweb-typst wordcount.nwm python > out.typ
typst compile out.typ
```
If `markup` is not on your `PATH`, you can call it via its full path. For example, on my system it lives at `/usr/lib/noweb/markup`.
## Example Output
`latex_out.pdf` is the LaTeX-rendered PDF from compiling the .tex output of `noweave wordcount.nw`.

`typst_out.pdf` is the Typst-rendered PDF from compiling the .typ output (out.typ) of this Typst backend.


Comparison of the two highlights some of the remaining deficiencies in this program. 

## Building
Run `cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug` to generate the build folder.

### TODO
- Support @quote and @endquote
- Improve Typst styling
