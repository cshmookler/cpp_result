# Declare project information
project(
    'cpp_result',
    'cpp',
    version : files('VERSION'),
    default_options : [ 'cpp_std=c++17' ],
)

# Project root and build directories
root_dir = meson.project_source_root()
build_dir = meson.project_build_root()
include_dir = root_dir / 'cpp_result'
src_dir = root_dir / 'src'
tests_dir = root_dir / 'tests'
examples_dir = root_dir / 'examples'

# Insert the project version into the version header file
conf_data = configuration_data()
conf_data.set('version', meson.project_version())
configure_file(
    configuration : conf_data,
    input : 'cpp_result' / 'version.hpp.in',
    output : 'version.hpp',
)

lib_cpp_result_headers = files(
    build_dir / 'version.hpp',
    include_dir / 'error.hpp',
    include_dir / 'result.hpp',
    include_dir / 'optional.hpp',
)
install_headers(lib_cpp_result_headers, subdir : 'cpp_result')

examples = [
    'error',
    'result',
    'optional',
]

foreach example_name : examples
    executable(
        'example_' + example_name,
        files(
            examples_dir / (example_name + '.cpp'),
        )
    )
endforeach

dep_gtest_main = dependency(
    'gtest_main',
    required : false,
    method : 'auto',
)

if dep_gtest_main.found()
    tests = [
        'version'
    ]

    foreach test_name : tests
        test_exec = executable(
            'test_' + test_name,
            files(
                tests_dir / (test_name + '.test.cpp'),
            ),
            dependencies : dep_gtest_main,
        )
        test(test_name, test_exec)
    endforeach
else
    warning('Skipping tests due to missing dependencies')
endif
