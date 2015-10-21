import webapp2
import os
import jinja2
import base_page
from google.appengine.ext import ndb
import db_defs

class View(base_page.BaseHandler):
    def __init__(self, request, response):
        self.initialize(request, response)
        self.template_values = {}

    def render(self, page):
        #self.template_values['pubkeys'] = [{'fullname':x.fullname,'key':x.key.urlsafe()} for x in db_defs.Public_Keys.query().fetch()]
        self.template_values['pubkeys'] = [{'fullname':x.fullname, 'key':x.key.urlsafe()} for x in db_defs.Public_Keys.query().fetch()]
        base_page.BaseHandler.render(self, 'view.html', self.template_values)

    def get(self):
        """Return a friendly HTTP greeting."""
        self.render('view.html')

    #def post(self):
class Ind(base_page.BaseHandler):
    def get(self):
        if self.request.get('type') == 'ind':
            pubkey_key = ndb.Key(urlsafe=self.request.get('key'))
            self.template_values = {'indkey':pubkey_key.get(), 'urlsafekey':self.request.get('key')}
            base_page.BaseHandler.render(self, 'ind.html', self.template_values)
        elif self.request.get('type') == 'edit':
            print 'In edit mode!'
            pubkey_key = ndb.Key(urlsafe=self.request.get('key'))
            self.template_values = {'edit':pubkey_key.get()}
            base_page.BaseHandler.render(self, 'main.html', self.template_values)



        #self.template_varibles['form_content'] = {}
        #template = JINJA_ENVIRONMENT.get_template('main.html')
        #for i in self.request.arguments():
        #    self.template_varibles['form_content'][i] = self.request.get(i)
        #self.response.write(template.render(self.template_varibles))
        #if action == '

