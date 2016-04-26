import webapp2
import os
import jinja2
import base_page
from google.appengine.ext import ndb
import db_defs
import test

class MainPage(base_page.BaseHandler):
    def __init__(self, request, response):
        self.initialize(request, response)
        self.template_varibles = {}

    def get(self):
        if self.request.get('action') == 'edit':
            print 'In edit mode!'
            pubkey_key = ndb.Key(urlsafe=self.request.get('key'))
            self.template_values = {'edit':pubkey_key.get(), 'urlsafe':self.request.get('key')}
            base_page.BaseHandler.render(self, 'main.html', self.template_values)
        else:
            self.render('main.html')

    def post(self):
        action = self.request.get('action')
        if action == 'add_key' or action == 'edit':
            if action == 'add_key':
                k = ndb.Key(db_defs.Public_Keys, self.app.config.get('default-key'))
                storekey = db_defs.Public_Keys(parent=k)
            else:
                print "Keyys" + self.request.get('editkey')
                storekey_key = ndb.Key(urlsafe=self.request.get('editkey'))
                storekey = storekey_key.get()
            storekey.fullname = self.request.get('full-name')
            storekey.email = self.request.get('email')
            storekey.comment = self.request.get('comment')
            storekey.encryptionType = self.request.get('Encryption-type')
            storekey.bit = int(self.request.get('bit-strength'))
            if self.request.get('exp-date') != '':
                storekey.expDate = self.request.get('exp-date')
            else:
                storekey.expDate = 'N/A'
            if self.request.get('exp-time') != '':
                storekey.expTime = self.request.get('exp-time')
            else:
                storekey.expTime = 'N/A'
            if self.request.get('expiration') != "False":
                storekey.exp = "True"
            else:
                storekey.exp = self.request.get('expiration')
            storekey.pubkey = self.request.get('pubkey')

            # IF DEBUGING ENABLED
            #if self.request.get('test') == 'True':
            error = test.debug(self)
            if error['is_err'] == 1:
               self.render('error.html', error)
            else:
                storekey.put()
                self.render('main.html', {'message':'Added ' + storekey.fullname + ' to the DataBase.'})
                if self.request.get('test'):
                    self.render('error.html', error)
                #self.render('error.html', {'fullname_err':'error'})
        else:
            self.render('main.html', {'message':'Action' + action + ' is unknown.'})



        #self.template_varibles['form_content'] = {}
        #template = JINJA_ENVIRONMENT.get_template('main.html')
        #for i in self.request.arguments():
        #    self.template_varibles['form_content'][i] = self.request.get(i)
        #self.response.write(template.render(self.template_varibles))
        #if action == '

