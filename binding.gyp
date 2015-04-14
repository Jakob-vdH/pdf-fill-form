{
    "targets": [
        {
            "target_name": "pdf_fill_form",
            "variables": {
                "myLibraries": "cairo poppler-qt4",
                "myIncludes": "QtCore"
            },            
            "sources": [
                "src/pdf-fill-form.cc",
                "src/NodePopplerAsync.cc",
                "src/NodePoppler.cc"
            ],
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions' ],
            "cflags": [
                "<!@(pkg-config --cflags <(myLibraries) <(myIncludes))"
            ],
            "xcode_settings": {
                'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                "OTHER_CFLAGS": [
                    "-fexceptions",
                    "<!@(pkg-config --cflags <(myLibraries) <(myIncludes))"
                ]
            },
            "libraries": [
                "<!@(pkg-config --libs <(myLibraries))"
            ],
            "include_dirs" : [
               "<!(node -e \"require('nan')\")"
            ]
        }
    ]
}
