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
    if record["domain_age_days"] < 365:
        sus += 2
    if record["port"] not in (80, 443):
        sus += 1

    if record["alexa_rank"] == None:
        sus = sus + 2
    elif record["alexa_rank"] > 500:
        sus += 1
    elif record["alexa_rank"] < 100:
        sus = sus - 1

    if record["file_extension"] not in ("html", "htm","php", "mp4", "flv"):
        sus += 1

    if record["num_domain_tokens"] > 3:
        sus += 1

    host = ""
    for c in record["host"]:
        if c == '.':
            c = ''
        host += c

    if host.isdigit() == True:
        sus += 2

    for i in range(0, len(record["path_tokens"])):
        path =["paypal", "google", "wallet", "amazon", "Google", "Amazon"]
        for p in  path:
            if record["path_tokens"][i].find(p) != -1:
                #print record["url"]
                sus += 1

    for i in range(0, len(record["domain_tokens"])-2):
        path =["paypal", "google", "wallet", "amazon", "Google", "Amazon"]
        for p in  path:
            if record["domain_tokens"][i].find(p) != -1:
                #print record["url"]
                sus += 1

    if record["path_len"] > 60:
        sus += 1

    if record["tld"] not in ('jp', 'com', 'org'):
        sus += 1

    if record["registered_domain"] == "yahoo.co.jp":
        sus = 0

    if sus > 3:
        bad += 1
        print "SUSPICIOUS",
        print record["host"]
    else:
        if record["malicious_url"] == 1:
            missed += 1

  corpus.close()
  ratio = (float(bad)/float(total)) * 100
  print "------------------------------------------------------------"
  print str(ratio) + "% Bad \nTotal:", total, "\nBad:", bad

if __name__ == "__main__":
  main(sys.argv[1:])
