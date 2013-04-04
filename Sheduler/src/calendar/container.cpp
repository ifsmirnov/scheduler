#include "container.hpp"

#include <iostream>

#include <QString>

namespace calendar_containers {

/*Container *Container::deserialize(QDomElement element)
{
    if (element.tagName() != "container") {
        std::cerr << "Not a container" << std::endl;
    }
    if (!element.hasAttribute("type")) {
        std::cerr << "Container type not specified" << std::endl;
    }

    QString type = element.attribute("type");

    if (type == "global") {
        GlobalContainer *container = new GlobalContainer;
        for (QDomElement child = element.firstChildElement("container");
             !child.isNull();
             child = child.nextSiblingElement("container")) {
            container->years[child.attribute("year")] =
                    dynamic_cast<YearContainer>(Container::deserialize(child));
        }
    }
    else if (type == "year") {
        // TODO
        return nullptr;
    }
    else if (type == "month") {
        // TODO
        return nullptr;
    }
    else {
        std::cerr << "Container type unknown" << std::endl;
        return nullptr;
    }
}*/

/*Container::Container()
{
}*/

} // calendar_containers
