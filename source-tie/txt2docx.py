import os
import sys
from docx import Document

def txt2docx(text_file):
  text_file = os.path.abspath(text_file)
  document = Document()
  file_contents = []
  with open(text_file) as fd:
    for line in fd:
      file_contents += line
  
  document.add_paragraph(file_contents)
  new_docx_file_path = os.path.splitext(text_file)[0] + '.docx'
  print(new_docx_file_path)
  document.save(new_docx_file_path)

if __name__ == '__main__':
  if len(sys.argv) < 2:
    print('plz give your txt file. like: `python txt2docx.py test.txt`')
    sys.exit(1)
  txt2docx(sys.argv[1])