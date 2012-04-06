import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Writer;
import javax.swing.AbstractAction;
import javax.swing.Action;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSeparator;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JWindow;
import javax.swing.KeyStroke;
import javax.swing.ScrollPaneConstants;

import org.python.core.*;
import org.python.util.PythonInterpreter;

/**
 * Simple Swing GUI to solicit commands and eval them in a Jython
 * interpreter.
 * Date: 2005.02.18
 * License: Public Domain
 * @author a=jsled; b=asynchronous.org; ${a}@${b}
 **/
public class JythonShell
{
    public static void main( String[] args )
        throws PyException
    {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                doGUI();
            }
        });
    }

    public static class JTextAreaWriter
        extends Writer
    {
        JTextArea _jta;
        public JTextAreaWriter( JTextArea jta )
        {
            super();
            _jta = jta;
        }

        public void close()
        {
            _jta = null;
        }

        public void flush()
        {
            /*nop*/
        }

        public void write( char[] cbuf, int off, int len )
        {
            if ( _jta == null )
                return;
            _jta.append( new String(cbuf,off,len) );
        }
    }

    public static void doGUI()
    {
        JFrame win;
        JPanel p;
        JTextArea outTa;
        final JTextArea inTa;
        final PythonInterpreter interp = new PythonInterpreter();
        final JTextAreaWriter jtaw;

        win = new JFrame( "jython" );
        win.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

        win.getContentPane().setLayout( new BoxLayout( win.getContentPane(), BoxLayout.Y_AXIS ) );
        outTa = new JTextArea( 50, 80 );
        outTa.setLineWrap(true);
        outTa.setFont( Font.decode( "Monospaced-PLAIN-12" ) );
        outTa.setEditable(false);

        jtaw = new JTextAreaWriter( outTa );
        interp.setOut(jtaw);
        interp.setErr(jtaw);

        inTa = new JTextArea( 3, 80 );
        inTa.setFont( Font.decode( "Monospaced-PLAIN-12" ) );
        Action evalAction = new AbstractAction()
            {
                public void actionPerformed( ActionEvent e )
                {
                    String cmd;
                    PyObject res;
                    try
                    {
                        cmd = inTa.getText();
                        jtaw.write( ">>> " + cmd + "\n" );
                        try
                        {
                            res = interp.eval( cmd );
                            jtaw.write( res.toString() + "\n" );
                        }
                        catch ( PyException exec )
                        {
                            if ( Py.matchException( exec, Py.SyntaxError ) )
                            {
                                try
                                {
                                    interp.exec( cmd );
                                }
                                catch ( PyException exec2 )
                                {
                                    jtaw.write( exec2.toString() );
                                    //exec2.printStackTrace( new PrintWriter(jtaw) );
                                }
                            }
                            else
                            {
                                jtaw.write( exec.toString() );
                                //exec.printStackTrace( new PrintWriter( jtaw ) );
                            }
                        }
                        finally
                        {
                            inTa.setText("");
                        }
                    }
                    catch ( IOException ioe )
                    {
                        throw new RuntimeException( "error writing prompt and cmd", ioe );
                    }
                }
            };
        inTa.getKeymap().addActionForKeyStroke(
            KeyStroke.getKeyStroke( "control ENTER" ),
            evalAction );
                
        win.getContentPane().add( new JScrollPane( outTa,
                                                   ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
                                                   ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED ) );
        win.getContentPane().add( new JSeparator() );
        win.getContentPane().add( new JScrollPane( inTa,
                                                   ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,
                                                   ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED ) );

        win.pack();
        win.setVisible(true);
    }
}
