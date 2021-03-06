#include "streamdata.h"

streamdata::streamdata()
{
}

// Qthread function used to allow streaming
class StreamThread : public QThread
{
    Q_OBJECT

protected:
    void run();
};

void StreamThread::run()
{
    while (true) {
        // open the file to the desktop and allow writing/reading of information
        QString outputFilename = "/Users/as_763/Desktop/output.txt";
        QString inputFilename = "/Users/as_763/Desktop/Tool Locations Dump.txt";
        QFile f_out(outputFilename);
        QFile f_in(inputFilename);
        f_out.open(QIODevice::WriteOnly | QIODevice::Text);
        f_in.open(QIODevice::ReadOnly | QIODevice::Text);

        // if opened the writing file wrong then return
        if(!f_out.isOpen()){
            qDebug() << "- Error, unable to open" << outputFilename << "for output" <<"\n";
            return;
        }

        // if opened the reading file wrong then return
        if(!f_in.isOpen()){
            qDebug() << "- Error, unable to open" << inputFilename << "for input" <<"\n";
            return;
        }

        // point a text stream at the file to allow writing and reading
        QTextStream outStream(&f_out);
        QTextStream inStream(&f_in);

        // tracker and placeholders to get the correct lines
        int tracker = 0;
        QString eigth = "";
        QString seventh = "";
        QString sixth = "";
        QString fifth = "";
        QString fourth = "";
        QString third = "";
        QString second = "";
        QString first = "";

        // loop that finds the last line while tracker the history of the past 8 lines
        while (!inStream.atEnd()) {
            eigth = seventh;
            seventh = sixth;
            sixth = fifth;
            fifth = fourth;
            fourth = third;
            third = second;
            second = first;
            first = inStream.readLine();
            tracker++;
        }

        // ouput the lines to write file
        outStream << eigth   << "\n";
        outStream << seventh << "\n";
        outStream << sixth   << "\n";
        outStream << fifth   << "\n";
        outStream << fourth  << "\n";
        outStream << third   << "\n";
        outStream << second  << "\n";
        outStream << first   << "\n";

        // close the files
        f_out.close();
        f_in.close();
    }
}
