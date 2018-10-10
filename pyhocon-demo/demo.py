'''
@File: demo.py
@Author: leon.li(l2m2lq@gmail.com)
@Date: 2018-10-10 16:26:27
@Last Modified By: leon.li(l2m2lq@gmail.com>)
@Last Modified Time: 2018-10-10 16:58:28
'''

import pyhocon
import json
import copy

def hocon_to_json():
  source = """
  a {
    a1: 2
  }
  b = 2
  c: "string_c"
  d: string_d
  """
  config = pyhocon.ConfigFactory.parse_string(source)
  # get value from key
  assert config.get("a.a1") == 2
  assert config.get("c") == "string_c"
  assert config.get("d") == "string_d"
  # to json string
  print(json.dumps(config))

def hocon_merge():
  source1 = """
  a {
    a1: 3
    a3: [1, 3]
  }
  """
  source2 = """
  a {
    a1: 4,
    a2: "string_a"
  }
  """
  source3 = """
  b {
    b1 = 4
  }
  """
  config1 = pyhocon.ConfigFactory.parse_string(source1)
  config2 = pyhocon.ConfigFactory.parse_string(source2)
  config3 = pyhocon.ConfigFactory.parse_string(source3)
  # config1and2 = pyhocon.ConfigTree.merge_configs(copy.deepcopy(config1), copy.deepcopy(config2))
  # print(json.dumps(config1))
  # print(json.dumps(config2))
  # print(json.dumps(config1and2))
  print(json.dumps(config3.with_fallback(config2).with_fallback(config1)))

def main():
  hocon_to_json()
  hocon_merge()

if __name__ == "__main__":
  main()