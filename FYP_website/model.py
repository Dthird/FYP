import web

db = web.database(dbn = 'sqlite', db = './sql/FYP.db')

def get_user(user_id):
    try:
        return db.select('user_info', where = 'user_id=$user_id', vars = locals())[0]
    except IndexError:
        return None

def update_attempts(user_id, attempts):
    db.update('user_info', where = 'user_id=$user_id', 
              vars = locals(), attempts = attempts)

def update_results(user_id, result_history, result_uploaded):
    db.update('user_info', where = 'user_id=$user_id', 
              vars = locals(), result_history = result_history, result_uploaded = result_uploaded)

'''
def new_post(title, text):
    db.insert('entries', title=title, content=text, posted_on=datetime.datetime.utcnow())

def del_post(id):
    db.delete('entries', where="id=$id", vars=locals())

def update_post(id, title, text):
    db.update('entries', where="id=$id", vars=locals(),
        title=title, content=text)
'''
