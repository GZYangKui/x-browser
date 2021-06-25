package cn.navigational.xbrowser.kit.util;


import org.dom4j.DocumentException;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.SAXReader;
import org.dom4j.io.XMLWriter;

import java.io.IOException;
import java.io.StringWriter;
import java.nio.charset.StandardCharsets;

public class XMLUtil {
    /**
     * 格式化xml字符串
     */
    public static String format(String xml) {
        var saxReader = new SAXReader();
        var str = xml;
        try {
            var document = saxReader.read(xml);
            var format = OutputFormat.createPrettyPrint();
            format.setEncoding(StandardCharsets.UTF_8.name());
            var out = new StringWriter();
            var writer = new XMLWriter();
            writer.write(document);
            str = out.toString();
        } catch (DocumentException | IOException e) {
            e.printStackTrace();
        }
        return str;
    }
}
