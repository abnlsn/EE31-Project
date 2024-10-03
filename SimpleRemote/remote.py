import requests


base_url = "http://ee31.eecs.tufts.edu/{}/{}"

while True:
    msg = input("New message number: ")
    r = requests.post(base_url.format("F392FC86D8D7", "F392FC86D8D7"), data={"msg": msg})
    print(r.url)