#! /usr/bin/env python

import sys
sys.path.insert( 0, '/home/pratap/tmp/sqlalchemy/lib/' )

import sqlalchemy as sql

metadata = sql.MetaData()
metadata1 = sql.MetaData()

users = Table( 'users', metadata,
            Column( 'user_id', Integer, primary_key = True ),
            Column( 'user_name', String(16), nullable = False ),
            Column( 'email_address', String(60), key='email' ),
            Column( 'password', String(20), nullable = False )
        )

user_prefs = Table( 'user_prefs', metadata,
                Column( 'pref_id', Integer, primary_key=True ),
                Column( 'user_id', Integer, ForeignKey("users.user_id"), nullable=False ),
                Column( 'pref_name', String(40), nullable=False ),
                Column( 'pref_value', String(100) )
        )

# a table with a composite primary key
invoices = Table( 'invoices', metadata,
            Column( 'invoice_id', Integer, primary_key=True ),
            Column( 'ref_num', Integer, primary_key=True ),
            Column( 'description', String(60), nullable=False )
        )
# a table with a composite foreign key referencing the parent table
invoice_items = Table( 'invoice_items', metadata,
                Column('item_id', Integer, primary_key=True),    
                Column('item_name', String(60), nullable=False),    
                Column('invoice_id', Integer, nullable=False),
                Column('ref_num', Integer, nullable=False),
                ForeignKeyConstraint(['invoice_id', 'ref_num'], ['invoices.invoice_id', 'invoices.ref_num'])
        )

# Retrieving the tables associated with a MetaData instance in the order of
# table dependency.
for t in metadata.table_iterator( reverse=False ):
    print t.name
for t in metadata.tables :
    print t.name

# Table, properties and columns.
employees = Table( 'employees', metadata,     
                Column('employee_id', Integer, primary_key=True),
                Column('employee_name', String(60), nullable=False, key='name'),
                Column('employee_dept', Integer, ForeignKey("departments.department_id"))
        )

# access the column "EMPLOYEE_ID":
employees.columns.employee_id

# or
justemployees.c.employee_id

# via string
employees.c['employee_id']

# iterate through all columns
for c in employees.c :
    print "Column", c

# get the table's primary key columns
for primary_key in employees.primary_key :    
    print "Primary key", primary_key

# get the table's foreign key objects:
for fkey in employees.foreign_keys :
    print "Foreign key", fkey

# access the table's MetaData
employees.metadata

# access the table's bound Engine or Connection, if its MetaData is bound
employees.bind

# access a column's name, type, nullable, primary key, foreign key
print "Column Employee ID - name", employees.c.employee_id.name
print "Column Employee ID - type", employees.c.employee_id.type
print "Column Employee ID - nullable", employees.c.employee_id.nullable
print "Column Employee ID - primary key ", employees.c.employee_id.primary_key
print "Column Employee dept - foreign key ", employees.c.employee_dept.foreign_key

# get the "key" of a column, which defaults to its name, but can
# be any user-defined string
employees.c.name.key

# access a column's table
employees.c.employee_id.table is employees

# get the table related by a foreign key
fcolumn = employees.c.employee_dept.foreign_key.column.table

# Bind a engine to metadata
engine = create_engine('sqlite://', **kwargs)
metadata.bind = engine
