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

        # If "id" is defined then update existing key. if not then assume creating a new PubKey
        if self.request.get('id'):
            try:
                new_key = ndb.Key(db_defs.Public_Keys, int(self.request.get('id'))).get()
            except AttributeError:
                self.response.status = 404
                self.response.status_message = "Invaild request with key " + str(self.request.get('id')) + " item not found."
                self.response.write("Invaild request with key " + str(self.request.get('id')) + " item not found.")
                return
        else:
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
            self.response.write("Invalid request, 'fullname' is required.")
            return
        #if bit:
        #    print "Bit strength is:" + bit
        #    new_key.bit = bit
        #else:
        #    self.response.status = 400
        #    self.response.status_message = "Invalid request, 'bit' is required."
        new_key.email = email
        new_key.comment = comment
        if exp != "False":
            new_key.exp = "True"
            if expDate:
                new_key.expDate = expDate
            else:
                self.response.status = 400
                self.response.status_message = "Invalid request, 'expDate' is required."
                self.response.write("Invalid request, 'expDate' is required.")
            if expTime:
                new_key.expTime = expTime
            else:
                self.response.status = 400
                self.response.status_message = "Invalid request, 'expTime' is required."
                self.response.write("Invalid request, 'expTime' is required.")
        else:
            new_key.expTime = 'N/A'
            new_key.expDate = 'N/A'
            new_key.exp = exp
        if pubkey:
            new_key.pubkey = pubkey
        else:
            self.response.status = 400
            self.response.status_message = "Invalid request, 'pubkey' is required."
            self.response.write("Invalid request, 'pubkey' is required.")

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
            #self.response.write(json.dumps(out))
            self.response.write("<pre>" + json.dumps(out, sort_keys=True, indent=4, separators=(',',':')) + "</pre>")
        else:
            q = db_defs.Public_Keys.query()
            keys = q.fetch(keys_only=True)
            #results = { 'keys' : [x.id() for x in keys]}
            #self.response.write(json.dumps(results))
            for i in keys:
                temp = i.get().to_dict()
                self.response.write("<pre>" + json.dumps(temp, sort_keys=True, indent=4, separators=(',',':')) + "</pre>")

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
        if self.request.get('id'):
            try:
                new_person = ndb.Key(db_defs.People, int(self.request.get('id'))).get()
            except AttributeError:
                self.response.status = 404
                self.response.status_message = "Invaild request with key " + str(kwargs['id']) + " item not found."
                self.response.write("Invaild request with key " + str(kwargs['id']) + " item not found.")
                return
        else:
            new_person = db_defs.People()

        fullname = self.request.get('full-name', default_value=None)
        email = self.request.get('email', default_value=None)
        phone = self.request.get('phone', default_value=None)
        address = self.request.get('address', default_value=None)
        contacts = self.request.get_all('contacts[]', default_value=None)

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
            for contact in contacts:
                new_person.contacts.append(ndb.Key(db_defs.People, contact))

        key = new_person.put()
        out = new_person.to_dict()
        self.response.write(json.dumps(out))

    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        if 'id' in kwargs:
            try:
                out = ndb.Key(db_defs.People, int(kwargs['id'])).get().to_dict()
            except AttributeError:
                self.response.status = 404
                self.response.status_message = "Invaild request with key " + str(kwargs['id']) + " item not found."
                self.response.write("Invaild request with key " + str(kwargs['id']) + " item not found.")
                return
            self.response.write(json.dumps(out))
        else:
            q = db_defs.People.query()
            keys = q.fetch(keys_only=True)
            #results = { 'keys' : [x.id() for x in keys]}
            #self.response.write(json.dumps(results))
            #self.response.write("<br>")
            for i in keys:
                temp = i.get().to_dict()
                self.response.write("<pre>" + json.dumps(temp, sort_keys=True, indent=4, separators=(',',':')) + "</pre>")
                #self.response.write("<hr>ID = " + str(i.id()) + "<br>")
                #self.response.write("Fullname = " + temp['fullname'] + "<br>")
                #self.response.write("Email = " + temp['email'] + "<br>")
                #self.response.write("Phone = " + temp['phone'] + "<br>")
                #self.response.write("Address = " + temp['address'] + "<br>")
                #self.response.write("Contacts = " + str(temp['contacts']) + "<br>")
                #self.response.write("URL = /people/" + str(i.id())  + "<br>")

class PubKeySearch(webapp2.RequestHandler):
    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        q = db_defs.Public_Keys.query()
        if kwargs['id']:
            q = q.filter(db_defs.Public_Keys.fullname == str(kwargs['id']))
            keys = q.fetch(keys_only=True)
        #results = { 'keys' : [x.id() for x in keys]}
        #self.response.write(json.dumps(results))
        if keys:
            for i in keys:
                temp = i.get().to_dict()
                self.response.write("<pre>" + json.dumps(temp, sort_keys=True, indent=4, separators=(',',':')) + "</pre>")
        else:
            self.response.status = 404
            self.response.status_message = "Invaild request with fullname " + str(kwargs['id']) + " item not found."
            self.response.write("Invaild request with fullname " + str(kwargs['id']) + " item not found.")


class PeopleSearch(webapp2.RequestHandler):
    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        q = db_defs.People.query()
        if kwargs['id']:
            q = q.filter(db_defs.People.fullname == str(kwargs['id']))
            keys = q.fetch(keys_only=True)
        #results = { 'keys' : [x.id() for x in keys]}
        #self.response.write(json.dumps(results))
        if keys:
            for i in keys:
                temp = i.get().to_dict()
                self.response.write("<pre>" + json.dumps(temp, sort_keys=True, indent=4, separators=(',',':')) + "</pre>")
        else:
            self.response.status = 404
            self.response.status_message = "Invaild request with fullname " + str(kwargs['id']) + " item not found."
            self.response.write("Invaild request with fullname " + str(kwargs['id']) + " item not found.")

class DelPeople(webapp2.RequestHandler):
    def get(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        if 'id' in kwargs:
            d = ndb.Key(db_defs.People, int(kwargs['id']))
            if d:
                d.delete()
                self.response.write("People: " + str(kwargs['id'] + "Deleted"))
            else:
                self.response.status = 404
                self.response.status_message = "Invaild request Delete with " + str(kwargs['id']) + " item not found."
                self.response.write("Invaild request with key " + str(kwargs['id']) + " item not found.")
                return
        else:
            self.response.status = 407
            self.response.status_message = "Invaild Delete, API needs a key."
            return

class DelPubKey(webapp2.RequestHandler):
    def post(self, **kwargs):
        if 'application/json' not in self.request.accept:
            self.response.status = 406
            self.response.status_message = "Invaild get, API only accepts application/json."
            return
        if 'id' in kwargs:
            d = ndb.Key(db_defs.PubKey, int(kwargs['id'])).get()
            if d:
                d.delete()
                self.response.write("PubKey: " + str(kwargs['id'] + "Deleted"))
            else:
                self.response.status = 404
                self.response.status_message = "Invaild request Delete with " + str(kwargs['id']) + " item not found."
                self.response.write("Invaild request Delete with " + str(kwargs['id']) + " item not found.")
                return
        else:
            self.response.status = 407
            self.response.status_message = "Invaild Delete, API needs a key."
            return



        #d = db_defs.People.
