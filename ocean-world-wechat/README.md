运行此项目需安装
```bash
pip3.6 install --upgrade pip
pip3.6 install werobot
pip3.6 install django
pip3.6 install whitenoise
```

初始化数据库

```bash
python3.6 manage.py migrate
```

重设admin密码

```bash
python3.6 manage.py createsuperuser
# 密码为admin123456
```

拷贝静态资源

```bash
python3.6 manage.py collectstatic
```

