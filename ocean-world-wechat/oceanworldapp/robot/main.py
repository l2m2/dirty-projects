import werobot
import config

robot = werobot.WeRoBot(config=config.cfg)

@robot.subscribe
def intro(message):
  return "欢迎您关注南宁融晟极地海洋世界!"


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


robot.run()