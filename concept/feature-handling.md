# Processing Features on a File

Given a Source file with a name, type and content, this file should be processed into it's targets liek so:

Rules:

1. Any single HEADER source file should result in a single HEADER target file
2. Any single C source file should result in a single C target file
3. Any single COMFY source file should result in one HEADER and one C target file.

Omnoml: 

    [<start>1]->[<choice>filetype?]
    [filetype?]-> comfy[generate header]
    [generate header]->[generate c-source]
    [filetype?]-> header[copy header as target]
    [filetype?]-> c source[copy c source as target]
    [generate c-source]->[for every target]
    [copy header as target]->[for every target]
    [copy c source as target]->[for every target|
    [<start>1]->[set modified = false]
    [set modified = false]->[for every feature|

    [<start>1]->[<choice>.   feature would modify?   .]
    [.   feature would modify?   .]-> yes[set modified = true]
    [set modified = true]->[feature: modify target]
    [feature: modify target]->[<end>2]
    [.   feature would modify?   .]-> no[2]

    ]
    [for every feature]->[<choice>modified?]
    [modified?]-> no[store file]
    [store file]->[<end>2]
    [modified?]-> yes[set modified = false]
    ]
    [for every target]->[<end>2]
