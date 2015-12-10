import web

db = web.database(dbn = 'sqlite', db = '../sql/FYP.db')
db.insert('user_info', user_id = 'admin_djx', pwd = 'djx', privilege = 1)
