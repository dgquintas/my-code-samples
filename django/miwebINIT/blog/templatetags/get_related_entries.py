from django.template import Library, Node, TemplateSyntaxError, Variable
from miweb.blog.models import Entry
from tagging.models import TaggedItem

register = Library()

class RelatedNode(Node):
  def __init__(self, entry, varname):
    self.varname = varname
    self.entry = Variable(entry)

  def render(self, context):
    entry = self.entry.resolve(context)
    context[self.varname] = TaggedItem.objects.get_related(entry, Entry)
    return ''

@register.tag
def get_related_entries(parser, token):
  bits = token.contents.split()
  print bits
  if len(bits) != 4:
    raise TemplateSyntaxError, "get_related_entries tag takes exactly four argument"
  if bits[2] != 'as':
    raise TemplateSyntaxError, "second argument to get_related_entries tag must be 'as'"

  return RelatedNode(bits[1], bits[3])



