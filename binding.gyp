{
  'targets': [
    {
      'target_name': 'uinput',
      'sources': [ 'src/uinput.cpp' ],
      'include_dirs': [
        '<!(node -e "require(\'nan\')")'
      ]
    }
  ]
}
