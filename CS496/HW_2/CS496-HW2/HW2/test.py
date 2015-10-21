import re

def debug(self):
    err_msg = {}
    rv = 0
    app_err = ''
    fullname_err = ''
    email_err = ''
    encryption_err = ''
    bitstrength_err = ''
    expDate_err = ''
    expTime_err = ''
    pubkey_err = ''


    # Check for blank statements
    if self.request.app.config.get('default-key') == '':
        app_err = 'default-key, not assigned'
        rv = 1
    if self.request.get('full-name') == '':
        fullname_err = 'fullname is blank '
        rv = 1
    if self.request.get('email') == '':
        email_err = 'email is blank '
        rv = 1
    if self.request.get('Encryption-type') == '':
        encryption_err = 'encryption type is blank '
        rv = 1
    if self.request.get('bit-strength') == '':
        bitstrength_err = 'bit strength is blank '
        rv = 1
    if self.request.get('expiration') != 'False':
        if self.request.get('exp-date') == '':
            expdate_err = 'expiration date is blank '
            rv = 1
        if self.request.get('exp-time') == '':
            exptime_err = 'expiration time is blank '
            rv = 1
    if self.request.get('pubkey') == '':
        pubkey_err = 'public key is blank '
        rv = 1

    # Check for invalid values
    if self.request.get('full-name').isdigit():
        err_msg['fullname_err'] = err_msg['fullname_err'] + 'fullname is a number '
        rv = 1
    #if not re.match(r"[^@]+@[^@]+\.[^@]+", self.request('email')):
    #    err_msg['email_err'] = err_msg['email_err'] + 'invalid email no @ sign'
    #    rv = 1
    #if self.request.get('Encryption-type') != 'RSA' or self.request.get('Encryption-type') != 'DSA':
    #    encryption_err = encryption_err + 'invalid Encryption-type'
    #    rv = 1
    #if not self.request.get('bit').isdigit():
    #    bitstrength_err = bitstrength_err + 'bit strength is not numeric'
    #    rv = 1
    #if self.request.get('pubkey').len() >= self.request.get('bit'):
    #    pubkey_err = pubkey_err + 'public key bit strenght does not match'
    #    rv = 1


    # Return strings
    err_msg['test'] = self.request.get('test')
    err_msg['is_err'] = rv
    err_msg['app_err'] = app_err
    err_msg['fullname_err'] = fullname_err
    err_msg['email_err'] = email_err
    err_msg['encryptiontype_err'] = encryption_err
    err_msg['bitstrength_err'] = bitstrength_err
    err_msg['expdate_err'] = expDate_err
    err_msg['exptime_err'] = expTime_err
    err_msg['pubkey_err'] = pubkey_err

    return err_msg

