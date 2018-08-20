import configparser
import subprocess

class BuildScheduler():
  def __init__(self):
    conf = configparser.ConfigParser()
    conf.read('config.ini')
    self.__qt_pro = conf.get('build', 'qt_pro')
    self.__build_dir = conf.get('build', 'build_dir')

  def __build_windows(self):
    p = subprocess.Popen('call "%VS140COMNTOOLS%"vsvars32.bat', shell=True, stderr = subprocess.PIPE)
    if p.returncode != 0:
      err = p.stderr.read()
      err = err.decode('gb2312')
      print(err)
      return False
    
    return True

  def __build_linux(self):
    pass

  def parse(self):
    pass

  def send_mail(self):
    pass

  def task(self):
    self.__build_windows()

if __name__ == "__main__":
  obj = BuildScheduler()
  obj.task()