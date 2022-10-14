project('bf2c', 'cpp',
    version : 'v0.1',
    default_options : ['cpp_std=c++20']
)

sources = [
    'src/main.cpp',
]

includes = include_directories('src')
conflict_dep = dependency('conflict')

executable('bf2c',
    dependencies : [conflict_dep],
    sources : sources,
    include_directories : includes
)