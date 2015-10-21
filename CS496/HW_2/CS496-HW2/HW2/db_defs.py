from google.appengine.ext import ndb

class Public_Keys(ndb.Model):
    fullname = ndb.StringProperty(required=True)
    email = ndb.StringProperty(required=True)
    comment = ndb.StringProperty(required=False)
    encryptionType = ndb.StringProperty(required=True)
    bit = ndb.IntegerProperty(required=True)
    expDate = ndb.StringProperty()
    expTime  = ndb.StringProperty()
    exp = ndb.StringProperty(required=True)
    pubkey = ndb.StringProperty(required=True)

