TEMPLATE = subdirs

SUBDIRS += \
    src \
    test \
    app

test.depends = src
app.depends = src
