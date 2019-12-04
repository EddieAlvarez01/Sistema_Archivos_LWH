#include "plotter.h"

Plotter::Plotter()
{

}

void Plotter::Plot_Mbr(Mbr mbr, std::string nameDisk, std::string path){
    std::string body = "";
    body += "<TR>\n" +
            std::string("<TD BGCOLOR=\"lightblue\">Nombre</TD>\n") +
            "<TD BGCOLOR=\"lightblue\">Valor</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>mbr_tamaño</TD>\n") +
            "<TD>" + std::to_string(mbr.mbr_size) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>mbr_fecha_creacion</TD>\n") +
            "<TD>" + mbr.dateTime + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>mbr_disk_signature</TD>\n") +
            "<TD>" + std::to_string(mbr.mbr_disk_aignature) + "</TD>\n" +
            std::string("</TR>\n");
    body += "<TR>\n" +
            std::string("<TD>Disk_fit</TD>\n") +
            "<TD>" + mbr.disk_fit + "</TD>\n" +
            std::string("</TR>\n");
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_start != -1){
            body += "<TR>\n" +
            std::string("<TD>part_status_") + std::to_string(x+1) + "</TD>\n" +
            "<TD>" + std::to_string(mbr.particions[x].part_status) + "</TD>\n" +
            std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_type_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + mbr.particions[x].part_type + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_fit_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + mbr.particions[x].part_fit + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_start_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + std::to_string(mbr.particions[x].part_start) + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_size_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + std::to_string(mbr.particions[x].part_size) + "</TD>\n" +
                    std::string("</TR>\n");
            body += "<TR>\n" +
                    std::string("<TD>part_name_") + std::to_string(x+1) + "</TD>\n" +
                    "<TD>" + mbr.particions[x].part_name + "</TD>\n" +
                    std::string("</TR>\n");
        }
    }
    std::string input = "digraph example {\n" +
                        std::string("node [shape=plaintext]\n") +
                        "rankdir=TB\n" +
                        std::string("A [label=<\n") +
                        "<TABLE BORDER=\"0\" CELLBORDER=\"1\" CELLSPACING=\"0\">\n" +
                        body +
                        "</TABLE>\n" +
                        ">];\n" +
                        "}";
    std::ofstream file;
    std::string pathTxt = path + ".txt";
    std::string pathJpg = path + ".png";
    file.open(pathTxt);
    if(file.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file << input << std::endl;
    file.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpng";
    system(pathUnion.c_str());
}

void Plotter::Plot_Disk(Mbr mbr, std::string path, int space){
    std::string body;
    int yy = 0;
    body += "<TD>MBR</TD>\n";
    for(int x=0; x<4; x++){
        if(mbr.particions[x].part_start == -1){
            yy++;
        }
    }
    for(int x=0; x<4; x++){
        body += "<TD>";
        if(mbr.particions[x].part_start != -1){
            if(strcmp(mbr.particions[x].part_type, "p") == 0){
                body += "Primaria<br/>" + std::to_string(mbr.particions[x].part_size * 100 / mbr.mbr_size) + "% del disco";
            }else if(strcmp(mbr.particions[x].part_type, "e") == 0){
                body += "Extendida<br/>" + std::to_string(mbr.particions[x].part_size * 100 / mbr.mbr_size) + "% del disco";
            }
        }else{
            body += "Libre<br/>" + std::to_string((space/yy) * 100 / mbr.mbr_size) + "% del disco";
        }
        body += "</TD>\n";
    }
    std::string input = "digraph test {\n" +
                        std::string("graph [ratio=fill];\n") +
                        "node [label=\"\\N\", fontsize=15, shape=plaintext]" +
                        std::string("graph [bb=\"0, 0, 352, 154\"];\n") +
                        "arset [label=<\n" +
                        std::string("<TABLE ALIGN=\"LEFT\">\n") +
                        "<TR>\n" +
                        body +
                        "</TR>\n" +
                        std::string("</TABLE>\n") +
                        ">, ];\n" +
                        "}";

    std::ofstream file;
    std::string pathTxt = path + ".txt";
    std::string pathJpg = path + ".png";
    file.open(pathTxt);
    if(file.fail()){
        std::cout << "Error al abrir el txt\n";
        return;
    }
    file << input << std::endl;
    file.close();
    std::string pathUnion = "dot " + pathTxt + " -o " + pathJpg + " -Tpng";
    system(pathUnion.c_str());
}
