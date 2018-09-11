'''
@File: txt2docx.py
@Author: leon.li(l2m2lq@gmail.com)
@Date: 2018-09-11 01:26:12
@Last Modified By: leon.li(l2m2lq@gmail.com>)
@Last Modified Time: 2018-09-11 02:04:10
'''

import os
import sys
from docx import Document

def valid_xml_char_ordinal(c):
  codepoint = ord(c)
  # conditions ordered by presumed frequency
  return (
    0x20 <= codepoint <= 0xD7FF or
    codepoint in (0x9, 0xA, 0xD) or
    0xE000 <= codepoint <= 0xFFFD or
    0x10000 <= codepoint <= 0x10FFFF
  )

def txt2docx(text_file):
  text_file = os.path.abspath(text_file)
  document = Document()
  file_contents = []
  with open(text_file, 'r', encoding='utf-8') as fd:
    for line in fd:
      file_contents += (''.join(c for c in line if valid_xml_char_ordinal(c)))
  document.add_paragraph(file_contents)
  new_docx_file_path = os.path.splitext(text_file)[0] + '.docx'
  document.save(new_docx_file_path)


if __name__ == '__main__':
  if len(sys.argv) < 2:
    print('plz give your txt file. like: `python txt2docx.py test.txt`')
    sys.exit(1)
  txt2docx(sys.argv[1])
