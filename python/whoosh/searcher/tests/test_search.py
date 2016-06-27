import unittest
import tempfile
import json

from search import Searcher


class TestSearch(unittest.TestCase):

    doc1 = {'path': '/foo/doc1',
            'keywords': 'document,one,foo',
            'title': 'Document one title.',
            'text': 'This is the a test document. Wot!'}

    doc2 = {'path': '/foo/doc2',
            'keywords': 'document,two,bar',
            'title': 'Document two title.',
            'text': 'Testing is cool, yo.'}

    def setUp(self):
        self.searcher = Searcher(tempfile.mkdtemp())
        self.searcher.add_documents(json.dumps((self.doc1, self.doc2)))

    def test_search_by_text(self):
        results = self.searcher.search('Wot')
        self.assertEqual(1, len(results))
        for fieldname, fieldvalue in results[0].items():
            self.assertEqual(self.doc1.get(fieldname), fieldvalue)

        # Now stemming. Document 2 only has "testing" in its body but it'll be
        # matched anyway because the "text" field of the schema uses the
        # StemmingAnalyzer.
        results = self.searcher.search('test')
        self.assertEqual(2, len(results))
        matched_doc_paths = [hit['path'] for hit in results]
        self.assertIn('/foo/doc1', matched_doc_paths)
        self.assertIn('/foo/doc2', matched_doc_paths)

    def test_search_by_keyword(self):
        # Simple search by a single keyword.
        results = self.searcher.search('keywords:one')
        self.assertEqual(1, len(results))  # doc1
        self.assertEqual(results[0]['path'], '/foo/doc1')

        # By two keywords.
        results = self.searcher.search('keywords:one,foo')
        self.assertEqual(1, len(results))  # doc1
        self.assertEqual(results[0]['path'], '/foo/doc1')

        # Keyword intersection.
        results = self.searcher.search('keywords:one,two')
        self.assertEqual(0, len(results))  # There are none.

        # Search for docs with a "one" keyword and "yo" in the body.
        results = self.searcher.search('keywords:one yo')
        self.assertEqual(0, len(results))  # There are none.

        # Anything with the "document" keyword.
        results = self.searcher.search('keywords:document')
        self.assertEqual(2, len(results))  # Both docs.

    def test_search_by_title(self):
        results = self.searcher.search('title:"Document one"')
        self.assertEqual(1, len(results))  # doc1
        self.assertEqual(results[0]['path'], '/foo/doc1')

if __name__ == '__main__':
    unittest.main()
