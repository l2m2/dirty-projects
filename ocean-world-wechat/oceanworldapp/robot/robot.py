from werobot import WeRoBot
from werobot.config import Config

import werobot

cfg = Config(
    SERVER='auto',
    HOST='0.0.0.0',
    PORT=80,
    SESSION_STORAGE=None,
    TOKEN='pXCtMZZ66J',
    APP_ID='wx8c53a82f87f6fe0d',
    APP_SECRET='dc9235aa8e7da02002221f1be221c7c6')

robot = WeRoBot(config=cfg)
client = werobot.client.Client(config=cfg)

web_get_code = 'https://open.weixin.qq.com/connect/oauth2/authorize?appid={appid}&redirect_uri={redirect_uri}&response_type=code&state={state}&scope={scope}'
web_get_code = web_get_code.format(appid=cfg['APP_ID'], redirect_uri='', state='', scope='snsapi_base')

@robot.subscribe
def intro(message):
    return "欢迎您关注南宁融晟极地海洋世界!"

@robot.view
def viewhander(message):
    print(message.source)
    userinfo = client.get_user_info(message.source)
    print(userinfo)
    return

@robot.key_click("introduction")
def introduction(message):
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("animal-science")
def animal_science(message):
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("show-time")
def show_time(message):
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("tour-guide")
def tour_guide(message):
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("activity")
def activity(message):
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("job-offers")
def job_offers(message):
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("award-research")
def award_research(message):
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("personal-center")
def personal_center(message):
    print(message.source)
    return "相关内容正在更新中，敬请期待。"


@robot.key_click("one-click-ticket-purchase")
def one_click_ticket_purchase(message):
    return "相关内容正在更新中，敬请期待。"
