from google.appengine.ext import ndb

class Model(ndb.Model):
    def to_dict(self):
        d = super(Model, self).to_dict()
        d['key'] = self.key.id()
        return d


class Public_Keys(Model):
    fullname = ndb.StringProperty(required=True)
    email = ndb.StringProperty(required=True)
    comment = ndb.StringProperty(required=False)
    #encryptionType = ndb.StringProperty(required=True)
    #bit = ndb.IntegerProperty(required=True)
    expDate = ndb.StringProperty()
    expTime  = ndb.StringProperty()
    exp = ndb.StringProperty(required=True)
    pubkey = ndb.StringProperty(required=True)
    google = ndb.StringProperty(required=False)


class People(Model):
    fullname = ndb.StringProperty(required=True)
    email = ndb.StringProperty(required=True)
    phone = ndb.StringProperty(required=True)
    address = ndb.StringProperty(required=True)
    contacts = ndb.KeyProperty(repeated=True)

    def to_dict(self):
        d = super(People,self).to_dict()
        d['contacts'] = [c.id() for c in d['contacts']]
        return d

