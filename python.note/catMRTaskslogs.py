
import requests
import re, sys
from bs4 import BeautifulSoup


if len(sys.argv) != 3:
    print "Usage: ./catMRTaskslogs.py taskUrl logUrl taskNumber "
    sys.exit(1)

# taskUrl = "http://hostname:port/jobhistory/task/task_1434848162092_722377_m_%06d"
taskUrl = sys.argv[1] + "%06d"

# logUrl = 'http://hostname:port'
logUrl = sys.argv[2]

for i in xrange(sys.argv[3]):
    r = requests.get(taskUrl % i)
    content = BeautifulSoup(r.text, "lxml")

    # print content.prettify()
    scriptTag = content.find_all('script',  attrs={"type": "text/javascript"})
    # print type(scriptTag[6].text)
    tableContent = scriptTag[6].text.strip().replace('\n','').replace('\r', '')

    # get the link of log file
    # match = re.match(r".*href=.*", tableContent);
    match = re.match(r".*href='(/jobhistory/[^']*).*", tableContent);
    if match:
        taskLogUrl = logUrl + match.group(1)

        r = requests.get(taskLogUrl)
        # print >> open("%06d" % i, 'w'), r.text
        print r.text
