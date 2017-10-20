Imports System
Imports System.IO
Imports System.Threading
Imports System.IO.Ports
Imports System.ComponentModel

Public Class Form1
    Dim myPort As Array
    Delegate Sub SetTextCallBack(ByVal [text] As String)

    Private Sub Form1_Load(sender As System.Object, e As System.EventArgs) Handles MyBase.Load
        myPort = IO.Ports.SerialPort.GetPortNames()
        ComboBox2.Items.AddRange(myPort)
        Button2.Enabled = False
        ' TextBox1.Enabled = False
        'Button3.Enabled = False
        Button4.Enabled = False
        Button5.Enabled = False
        ' CloseToolStripMenuItem.Enabled = True
        ComboBox1.SelectedIndex = 0
        ComboBox2.SelectedIndex = 0
        ComboBox3.SelectedIndex = 0
        ComboBox4.SelectedIndex = 0
        ComboBox5.SelectedIndex = 0
    End Sub

    Private Sub Button1_Click(sender As System.Object, e As System.EventArgs) Handles Button1.Click
        SerialPort1.PortName = ComboBox2.Text
        SerialPort1.BaudRate = ComboBox1.Text
        SerialPort1.DataBits = ComboBox3.Text
        SerialPort1.Parity = ComboBox4.SelectedValue
        SerialPort1.StopBits = ComboBox5.Text
        SerialPort1.Open()

        Button1.Enabled = False
        Button2.Enabled = True
        ' Button3.Enabled = True
        Button4.Enabled = True
        Button5.Enabled = True
        ' TextBox1.Enabled = True
        ComboBox1.Enabled = False
        ComboBox2.Enabled = False
        ComboBox3.Enabled = False
        ComboBox4.Enabled = False
        ComboBox5.Enabled = False
        '   CloseToolStripMenuItem.Enabled = False

    End Sub

    Private Sub Button2_Click(sender As System.Object, e As System.EventArgs) Handles Button2.Click
        SerialPort1.Close()
        Button1.Enabled = True
        Button2.Enabled = False
        '    Button3.Enabled = False
        Button4.Enabled = False
        Button5.Enabled = False
        '   TextBox1.Enabled = False
        ComboBox1.Enabled = True
        ComboBox2.Enabled = True
        ComboBox3.Enabled = True
        ComboBox4.Enabled = True
        ComboBox5.Enabled = True
        '  CloseToolStripMenuItem.Enabled = True
        
    End Sub

    '  Private Sub Button3_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
    '      SerialPort1.Write(TextBox1.Text)
    '    TextBox1.Clear()
    ' End Sub

    Private Sub SerialPort1_DataReceived(ByVal sender As System.Object, ByVal e As System.IO.Ports.SerialDataReceivedEventArgs) Handles SerialPort1.DataReceived
        ReceivedText(SerialPort1.ReadExisting())
    End Sub
    Private Sub ReceivedText(ByVal [text] As String)

        If Me.RichTextBox1.InvokeRequired Then
            Dim x As New SetTextCallBack(AddressOf ReceivedText)
            Me.Invoke(x, New Object() {(text)})
        Else
            Me.RichTextBox1.Text &= [text]
            RichTextBox1.SelectionStart = RichTextBox1.TextLength
            RichTextBox1.ScrollToCaret()
        End If
    End Sub


    Private Sub Button4_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button4.Click
        SerialPort1.Write("a" & vbCr)
    End Sub

    Private Sub Button5_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button5.Click
        SerialPort1.Write("s" & vbCr)
    End Sub

    Private Sub CloseToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        Close()
    End Sub

    Private Sub AboutToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        MessageBox.Show("Proiect Sincretic" & Environment.NewLine & "" & Environment.NewLine & " TUDOR FOFIU" & Environment.NewLine & "" & Environment.NewLine & "Anul III" & Environment.NewLine & "Ingineria Sistemelor" & Environment.NewLine & "2012",
                        "About", MessageBoxButtons.OK,
                        MessageBoxIcon.Question)
    End Sub

    Private Sub Button6_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button6.Click
        RichTextBox1.Clear()
    End Sub

    Private Sub ComboBox2_SelectedIndexChanged(sender As Object, e As EventArgs) Handles ComboBox2.SelectedIndexChanged

    End Sub

    Private Sub GroupBox2_Enter(sender As Object, e As EventArgs) Handles GroupBox2.Enter

    End Sub
End Class
