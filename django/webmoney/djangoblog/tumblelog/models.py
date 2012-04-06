from django.db import models
from django.contrib.contenttypes import generic
from django.db.models import signals
from django.contrib.contenttypes.models import ContentType
from django.dispatch import dispatcher
from blog.models import Entry
from links.models import Link


class TumbleItem(models.Model):
    content_type = models.ForeignKey(ContentType)
    object_id = models.PositiveIntegerField()
    pub_date = models.DateTimeField()
    content_object = generic.GenericForeignKey('content_type', 'object_id')

    class Meta:
        ordering = ('-pub_date',)
    
    def __unicode__(self):
        return self.content_type.name

def create_tumble_item(sender, instance, signal, *args, **kwargs):
	if 'created' in kwargs:
		if kwargs['created']:
			create = True
			ctype = ContentType.objects.get_for_model(instance)
			if ctype.name == 'link':
				pub_date = instance.date
			else:
				pub_date = instance.pub_date
			if create:
				t = TumbleItem.objects.get_or_create(content_type=ctype, object_id=instance.id, pub_date=pub_date)



for modelname in [Entry, Link]:		
	dispatcher.connect(create_tumble_item, signal=signals.post_save, sender=modelname)

