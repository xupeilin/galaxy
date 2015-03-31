# -*- coding:utf-8 -*-
from django.conf import urls

urlpatterns = urls.patterns('bootstrap.views',
     (r'^$', 'index'),
)

urlpatterns += urls.patterns('',
     (r'^conf/', urls.include('console.conf.urls')),
)

urlpatterns += urls.patterns('',
     (r'^service/', urls.include('console.service.urls')),
)

urlpatterns += urls.patterns('',
     (r'^taskgroup/', urls.include('console.taskgroup.urls')),
)
