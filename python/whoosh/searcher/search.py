import os
import os.path
import json

from whoosh import index
from whoosh.analysis import StemmingAnalyzer
from whoosh.fields import Schema, TEXT, KEYWORD, ID
from whoosh.qparser import QueryParser


class Searcher(object):
    def __init__(self, index_path):
        self._schema = self._get_schema()
        self._qparser = QueryParser("text", schema=self._schema)
        self._index = self._get_index(index_path, self._schema)

    def add_documents(self, docs):
        """Adds all given docs to the index.

        Args:
            docs: A JSON-encoded sequence of documents. Documents may be
                missing some of the schema fields, but it's an error to have
                extra fields not present in the schema.
        """
        ddocs = json.loads(docs)
        with self._index.writer() as w:
            for doc in ddocs:
                # doc ~ dictionary of fieldname-fieldvalue.
                w.add_document(**doc)

    def update_documents(self, paths):
        raise NotImplemented

    def search(self, query):
        q = self._qparser.parse(query)
        with self._index.searcher() as searcher:
            results = searcher.search(q)
            return self._parse_results(results)

    @staticmethod
    def _get_schema():
        return Schema(path=ID(stored=True),
                      title=TEXT(stored=True),
                      keywords=KEYWORD(lowercase=True,
                                       commas=True),
                      text=TEXT(analyzer=StemmingAnalyzer()))

    @staticmethod
    def _get_index(index_path, schema):
        if index.exists_in(index_path):
                return index.open_dir(index_path)
        else:
            if not os.path.exists(index_path):
                os.mkdir(index_path)
            return index.create_in(index_path, schema)

    @staticmethod
    def _parse_results(results):
        return [hit.fields() for hit in results]
