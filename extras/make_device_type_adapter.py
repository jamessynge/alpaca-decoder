#!/usr/bin/env python3
"""Generate a DeviceImplBase subclass for a specified device type.

This is very much a work in progress; really, just at the beginning.

See ../README.md for ideas on what this will do.
"""

import os
import pprint
import sys
from typing import Any, Dict, List, Union

import dataclasses
import requests
import yaml

Spec = Dict[str, Union['Spec', str, int, List['Spec']]]


def get_spec() -> str:
  """Reach Alpaca Device spec from local cache with fallback to URL fetch."""
  local_copy = os.path.join(os.path.expanduser('~'), 'AlpacaDeviceAPI_v1.yaml')
  if os.path.exists(local_copy):
    with open(local_copy, 'r') as f:
      text = f.read()
    print(f'Read spec from cache file {local_copy}')
  else:
    response = requests.get(
        'https://www.ascom-standards.org/api/AlpacaDeviceAPI_v1.yaml')
    text = response.text
    with open(local_copy, 'w') as f:
      f.write(response.text)
    print(f'Cached spec in file {local_copy}')
  return text


def make_components_map(spec: Spec) -> Dict[str, Spec]:
  result: Dict[str, Spec] = {}
  all_components = spec['components']
  for component_type, components_of_type in all_components.items():
    for component_name, component_def in components_of_type.items():
      ref = f'#/components/{component_type}/{component_name}'
      result[ref] = component_def
  return result


@dataclasses.dataclass()
class Schema(object):
  type_: str


@dataclasses.dataclass()
class Parameter(object):
  """Represents a named value in an HTTP request path or query string.

  Parameters in a request are positional, with that position specified by name
  in a path template; for example '{device_number}' in
  '/camera/{device_number}/action' indicates that the parameter named
  'device_number' appears at that position in the path.

  Parameters in the query string are identified by name and can appear in any
  order, with unknown parameters ignored by the server. Their format is
  name=value, with '&' as a separator between parameters.
  """
  name: str


class Property(object):
  """Represents a named value provided in an HTTP request or response body."""


class AlpacaSpec(object):

  def __init__(self, spec: Spec):
    self.spec = spec
    print('spec keys:', self.spec.keys())
    self.paths = spec['paths']
    self.components: Dict[str, Spec] = make_components_map(spec)
    print('components keys:\n\t', end='')
    print('\n\t'.join(sorted(self.components.keys())))
    self.resolve_re = None

  def _resolve_value_refs(self, obj: object):
    pass

  def _resolve_elem_refs(self, lst: List[Any]):
    pass


def main(argv: List[str]):
  text = get_spec()
  raw_spec = yaml.safe_load(text)

  spec = AlpacaSpec(yaml.safe_load(text))

  action = spec.paths['/{device_type}/{device_number}/action']
  put = action['put']
  pprint.pprint(put, indent=1)

  # make_components_map(spec)


#   print(list(spec.keys()))

#   get_obj = spec['paths']['/telescope/{device_number}/destinationsideofpier']['get']
#   print(get_obj['parameters'])

if __name__ == '__main__':
  main(sys.argv[:])
