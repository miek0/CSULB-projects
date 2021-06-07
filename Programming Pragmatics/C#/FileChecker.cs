/*
 * Mike Zeng
 * cecs 424-05
 * Assignment 4
 */
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Xml.Linq;

namespace _424assignment4
{
    class Program
    {
        static IEnumerable<string> EnumerateFilesRecursively(string path)
        { 
            return Directory.GetFiles(path, "*.*", SearchOption.AllDirectories);
        }

        static string FormatByteSize(long byteSize)
        {
            string[] size_units = { "B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB" };    //array of unit strings to append
            if (byteSize == 0)      //handling 0 byte situations
                return "0" + size_units[0];
            int return_unit = 0;    //iterator to select unit
            double return_byte = byteSize;
            while(return_byte > 1000 && return_unit < size_units.Length - 1)   //bytes must be >= 1 and < 1000
            {
                return_unit++;
                return_byte /= 1000;
            }
            return return_byte.ToString("0.00 ")+size_units[return_unit];   //truncate to 2 decimals and appends the unit
        }

        static XDocument CreateReport(IEnumerable<string> files)
        {
            //files are grouped by their extensions
            var grouped_files =
                from f in files
                group f by Path.GetExtension(f).ToLower() into exts         //grouped into sequence exts with 3 fields
                select new
                {
                    ext_type = exts.Key,                                    //type of extension
                    file_count = exts.Count(),                              //total count of that file ext
                    total_bytes = exts.Sum(x => new FileInfo(x).Length)     //total byte size of all files
                };

            //for console testing
            foreach (var a in grouped_files)
            {
                Console.WriteLine(a.ToString());
            }

            //creates HTML file to display the report
            XDocument html_report =
                new XDocument(
                    new XElement("html",
                            new XElement("head",
                            new XElement("title", "File Report"),
                            new XElement("style", " table, th, td { border: 1px solid black; } ")
                            ),
                        new XElement("body",
                            new XElement("table", new XAttribute("border",1),
                                new XElement("thead",
                                    new XElement("tr",
                                        new XElement("td", "Type"),
                                        new XElement("td", "Count"),
                                        new XElement("td", "Total Size"))),
                                new XElement("tbody",
                                    from f in grouped_files
                                    orderby f.total_bytes descending
                                    select new XElement("tr",
                                        new XElement("td", f.ext_type),    
                                        new XElement("td", new XAttribute("align", "right"), f.file_count.ToString()),
                                        new XElement("td", new XAttribute("align", "right"), FormatByteSize(f.total_bytes))))))));                                        
            html_report.Save(@"C:\Users\meikz\Desktop\reports\report.html");    //saved to file location to use in main

            return html_report;
        }

        public static void Main(string[] args)
        {
            //command line inputs
            Console.WriteLine("Enter input folder path: ");
            var folderpath = @"" + Console.ReadLine();
            Console.WriteLine("Enter HTML file path: ");
            var HTMLreport = @"" + Console.ReadLine();

            CreateReport(EnumerateFilesRecursively(folderpath));    //generates the XML into a XDoc to open (saved into html file)
            System.Diagnostics.Process.Start(@"cmd.exe ", @"/C" + HTMLreport);  //opens the html file containing the data on a browser
        }
    }
}
