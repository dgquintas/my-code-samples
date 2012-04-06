from django.db import models

from tagging.fields import TagField
from tagging.models import Tag

class Link(models.Model):
    title = models.CharField(max_length=200)
    description = models.TextField()
    url = models.CharField(max_length=400)
    date = models.DateTimeField('Date published')
    tags = TagField()
    
    class Meta:
        ordering = ('-date',)
        get_latest_by = 'date'

    def __unicode__(self):
        return u'%s' %(self.title)

    def get_absolute_url(self):
        return "/link/%s/" %(self.id)
    
    def get_tags(self):
        return Tag.objects.get_for_object(self)

