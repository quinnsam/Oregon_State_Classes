import webapp2
from google.appengine.ext import ndb
import db_defs
import json

class PubKey(webapp2.RequestHandler):
    def post(self):
        fullname = ''
        email = ''
        comment = ''
        encryptionType = ''
        bit = ''
        expDate = ''
        expTime = ''
        exp = ''
        pubkey = ''
        print "made it here"
        """ Creates a Public Key object

            POST Body Variables:
                full-name - [required] fullname
                email - [optional] email
                comment - [optional] comment
                Encryption-type - [required] encryptionType
                bit-sterngth - [required] bit
                expiration - [required] exp
                exp-date - [optional] expDate
                exp-time - [optional] expTime
                pubkey - [required] pubkey
        """

        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Not Acceptable, API only supports Application Json MIME type."
            return
        new_key = db_defs.Public_Keys()

        fullname = self.request.get('full-name', default_value=None)
        email = self.request.get('email', default_value=None)
        comment = self.request.get('comment', default_value=None)
        encryptionType = self.request.get('Encryption-type', default_value=None)
        bit = self.request.get('bit-strength', default_value=None)
        expDate = self.request.get('exp-date', default_value=None)
        expTime = self.request.get('exp-time', default_value=None)
        exp = self.request.get('expiration', default_value=None)
        pubkey = self.request.get('pubkey', default_value=None)

        if fullname:
            print "Fullname is:" + fullname
            new_key.fullname = fullname
        else:
            self.response.status = 400
            self.response.status_message = "Invalid request, 'fullname' is required."
        #if bit:
        #    print "Bit strength is:" + bit
        #    new_key.bit = bit
        #else:
        #    self.response.status = 400
        #    self.response.status_message = "Invalid request, 'bit' is required."
        if email:
            new_key.email = email
        if comment:
            new_key.comment = comment
        if exp != "False":
            new_key.exp = "True"
            if expDate:
                new_key.expDate = expDate
            else:
                self.response.status = 400
                self.response.status_message = "Invalid request, 'expDate' is required."
            if expTime:
                new_key.expTime = expTime
            else:
                self.response.status = 400
                self.response.status_message = "Invalid request, 'expTime' is required."
        else:
            new_key.expTime = 'N/A'
            new_key.expDate = 'N/A'
            new_key.exp = exp
        if pubkey:
            new_key.pubkey = pubkey
        else:
            self.response.status = 400
            self.response.status_message = "Invalid request, 'pubkey' is required."

        key = new_key.put()
        out = new_key.to_dict()
        self.response.write(json.dumps(out))

    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        if 'id' in kwargs:
            out = ndb.Key(db_defs.Public_Keys, int(kwargs['id'])).get().to_dict()
            self.response.write(json.dumps(out))
        else:
            q = db_defs.Public_Keys.query()
            keys = q.fetch(keys_only=True)
            results = { 'keys' : [x.id() for x in keys]}
            self.response.write(json.dumps(results))

class People(webapp2.RequestHandler):
    def post(self):
        fullname = ''
        email = ''
        phone = ''
        address = ''
        contacts = []

        """ Creates a Public Key object

            POST Body Variables:
                full-name - [required] fullname
                email - [optional] email
                phone - [optional] comment
                address - [required] encryptionType
                contacts - [required] bit
        """

        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Not Acceptable, API only supports Application Json MIME type."
            return
        new_person = db_defs.People()

        fullname = self.request.get('full-name', default_value=None)
        email = self.request.get('email', default_value=None)
        phone = self.request.get('phone', default_value=None)
        address = self.request.get('address', default_value=None)
        contacts = self.request.get('contacts', default_value=None)

        if fullname:
            new_person.fullname = fullname
        else:
            self.response.status = 400
            self.response.status_message = "Invalid request, 'fullname' is required."
        if email:
            new_person.email = email
        if phone:
            new_person.phone = phone
        if address:
            new_person.address = address
        if contacts:
            new_person.contacts = contacts

        key = new_person.put()
        out = new_person.to_dict()
        self.response.write(json.dumps(out))

    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        if 'id' in kwargs:
            out = ndb.Key(db_defs.People, int(kwargs['id'])).get().to_dict()
            self.response.write(json.dumps(out))
        else:
            q = db_defs.People.query()
            keys = q.fetch(keys_only=True)
            results = { 'keys' : [x.id() for x in keys]}
            self.response.write(json.dumps(results))

class PublicKeySearch(webapp2.RequestHandler):
    def post(self):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        q = db_defs.Public_Keys.query()
        if self.request.get('full-name',None):
            q = q.filter(db_defs.Public_Keys.fullname == self.request.get('full-name'))
        keys = q.fetch(keys_only=True)
        results = { 'keys' : [x.id() for x in keys]}
        self.response.write(json.dumps(results))

