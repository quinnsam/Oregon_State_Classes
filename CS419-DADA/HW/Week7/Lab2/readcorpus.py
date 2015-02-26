#!/usr/bin/python

import json, sys, getopt, os
def usage():
  print("Usage: %s --file=[filename]" % sys.argv[0])
  sys.exit()

def main(argv):

  file=''

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

    # Do something with the URL record data...
    sus = 0
    if record["domain_age_days"] < 100:
        sus += 1
    if record["port"] != 80:
        sus += 1

    if record["alexa_rank"] > 500:
        sus += 1

    if record["file_extension"] != "html":
        sus += 1

    if record["num_domain_tokens"] > 5:
        sus += 1

    for path in record["path_tokens"]:
        if path == "paypal" or path == "google" or path == "wallet":
            sus += 1

    if sus > 3:
        print "SUSPISIOUS",
        print record["registered_domain"], record["domain_age_days"] #, record["ips["ip"]"]

  corpus.close()

if __name__ == "__main__":
  main(sys.argv[1:])
