# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))


# -- Project information -----------------------------------------------------

project = 'concrete'
copyright = '2022, Henrik Steffen Gaßmann'
author = 'Henrik Steffen Gaßmann'

# The full version, including alpha/beta/rc tags
release = '0.0.0-alpha.4'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "sphinx_multiversion",
]
primary_domain = 'cpp'
highlight_language = 'cpp'
cpp_index_common_prefix = [
    'dplx::cncr',
]

# Add any paths that contain templates here, relative to this directory.
templates_path = [
    '_templates',
]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []

smv_tag_whitelist = None
smv_branch_whitelist = "^(master|release/v.+)$"
smv_remote_whitelist = "^origin$"


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'furo'
html_theme_options = {
    # "light_css_variables": {
    #     "font-stack--monospace": "Fira Code, Cascadia Code, \"SFMono-Regular\", Menlo, Consolas, Monaco, Liberation Mono, Lucida Console, monospace",
    # },
    # "dark_css_variables": {
    #     "font-stack--monospace": "Fira Code, Cascadia Code, \"SFMono-Regular\", Menlo, Consolas, Monaco, Liberation Mono, Lucida Console, monospace",
    # },
}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['_static']
html_css_files = [
    'css/custom.css',
]