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
                "type": "view",
                "name": "集团官网",
                "url": "http://www.tianheplaza.com/"
            }, {
                "type": "click",
                "name": "景区介绍",
                "key": "introduction"
            }, {
                "type": "click",
                "name": "动物科普",
                "key": "animal-science"
            }, {
                "type": "click",
                "name": "表演时间",
                "key": "show-time"
            }, {
                "type": "click",
                "name": "游览攻略",
                "key": "tour-guide"
            }]
        }, {
            "name":
            "最新信息",
            "sub_button": [{
                "type": "click",
                "name": "主题活动",
                "key": "activity"
            }, {
                "type": "click",
                "name": "招聘信息",
                "key": "job-offers"
            }, {
                "type": "click",
                "name": "有奖调研",
                "key": "award-research"
            }]
        }, {
            "name":
            "购票服务",
            "sub_button": [{
                "type": "click",
                "name": "个人中心",
                "key": "personal-center"
            }, {
                "type": "click",
                "name": "一键购票",
                "key": "one-click-ticket-purchase"
            }]
        }]
    })
