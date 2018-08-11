import werobot
import config

if __name__ == "__main__":
    robot = werobot.WeRoBot(config=config.cfg)
    client = robot.client
    client.create_menu({
        "button": [{
            "name":
            "入园必看",
            "sub_button": [{
                "type": "click",
                "name": "集团官网"
            }, {
                "type": "click",
                "name": "景区介绍"
            }, {
                "type": "click",
                "name": "动物科普"
            }, {
                "type": "click",
                "name": "表演时间"
            }, {
                "type": "click",
                "name": "游览攻略"
            }]
        }, {
            "name":
            "最新信息",
            "sub_button": [{
                "type": "click",
                "name": "主题活动"
            }, {
                "type": "click",
                "name": "招聘信息"
            }, {
                "type": "click",
                "name": "有奖调研"
            }]
        }, {
            "name":
            "购票服务",
            "sub_button": [{
                "type": "click",
                "name": "个人中心"
            }, {
                "type": "click",
                "name": "一键购票"
            }]
        }]
    })
