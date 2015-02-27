#!/usr/bin/python

import json, sys, getopt, os
def usage():
  print("Usage: %s --file=[filename]" % sys.argv[0])
  sys.exit()

def main(argv):

  file=''
  total = 0
  bad = 0
  false = 0
  missed = 0

  myopts, args = getopt.getopt(sys.argv[1:], "", ["file="])

  for o, a in myopts:
    if o in ('-f, --file'):
      file=a
    else:
      usage()

  if len(file) == 0:
    usage()

  corpus = open(file)
  urldata = json.load(corpus, encoding="latin1")

  for record in urldata:
    total += 1

    # Do something with the URL record data...
    sus = 0
    if record["domain_age_days"] < 50:
        sus += 1
    if record["port"] != 80:
        sus += 1

    if record["alexa_rank"] > 500:
        sus += 1

    if record["file_extension"] != ("html" or "htm"):
        sus += 1

    if record["num_domain_tokens"] > 3:
        sus += 1

    for i in range(0, len(record["path_tokens"])):
    #for path in record["path_tokens"]:
        path =["paypal", "google", "wallet", "amazon", "Google", "Amazon"]
        for p in  path:
            if record["path_tokens"][i].find(p) != -1:
                print record["url"]
                sus += 1

    for i in range(0, len(record["domain_tokens"])-1):
    #for path in record["path_tokens"]:
        path =["paypal", "google", "wallet", "amazon", "Google", "Amazon"]
        for p in  path:
            if record["domain_tokens"][i].find(p) != -1:
                print record["url"]
                sus += 1

    if record["url_len"] > 40:
        sus += 1

    if record["tld"] != 'com':
        sus += 1

    if sus > 3:
        if record["malicious_url"] == 1:
            bad += 1
        else:
            false += 1
        print "SUSPISIOUS",
        print record["host"] #, record["ips["ip"]"]
    else:
        if record["malicious_url"] == 1:
            missed += 1

  corpus.close()
  ratio = (float(bad)/float(total)) * 100
  print "------------------------------------------------------------"
  print str(ratio) + "% Bad \nFalse:", false, 'Missed:', missed#, total, bad

if __name__ == "__main__":
  main(sys.argv[1:])
