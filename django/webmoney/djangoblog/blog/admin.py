from django.contrib import admin

from djangoblog.blog.models import Entry

class EntryAdmin(admin.ModelAdmin):
    list_display = ('title', 'pub_date', 'enable_comments', 'status')
    search_fields = ['title', 'body_markdown']
    list_filter = ('pub_date', 'enable_comments', 'status')
    prepopulated_fields = {"slug": ('title', ) }
    fieldsets = (
		(None, 
            {'fields': (
                ('title', 'status'), 
                'body_markdown', 
                ('pub_date', 'enable_comments'), 
                'tags', 
                'slug'
                )
            }
        ),
    )

admin.site.register(Entry, EntryAdmin)

