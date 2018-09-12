'''
@File: main.py
@Author: leon.li(l2m2lq@gmail.com)
@Date: 2018-09-12 16:33:05
@Last Modified By: leon.li(l2m2lq@gmail.com>)
@Last Modified Time: 2018-09-12 17:23:46
'''


class Solution:
  def romanToInt(self, s):
    """
    :type s: str
    :rtype: int
    """
    # Symbol       Value
    # I             1
    # V             5
    # X             10
    # L             50
    # C             100
    # D             500
    # M             1000
    dict_buff = {
      'M': 1000, 'CM': 900, 'D': 500, 'CD': 400, 'C': 100, 
      'XC': 90, 'L': 50, 'XL': 40, 'X': 10, 
      'IX': 9, 'V': 5, 'IV': 4, 'I': 1
    }
    k = dict_buff.keys()
    num = 0
    while s:
      if s[0:2] in k:
        num += dict_buff[s[0:2]]
        s = s[2:]
        continue
      num += dict_buff[s[0]]
      s = s[1:]
    return num

if __name__ == "__main__":
  so = Solution()
  print(so.romanToInt('III') == 3)
  print(so.romanToInt('IV') == 4)
  print(so.romanToInt('IX') == 9)
  print(so.romanToInt('LVIII') == 58)
  print(so.romanToInt('MCMXCIV') == 1994)
        